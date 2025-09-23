#!/bin/bash
# N8N Deployment Script for K3s Cluster

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_header() {
    echo -e "${BLUE}[DEPLOY]${NC} $1"
}

# Check if kubectl is available
check_kubectl() {
    if ! command -v kubectl &> /dev/null; then
        print_error "kubectl is not installed or not in PATH"
        exit 1
    fi
    
    # Check cluster connectivity
    if ! kubectl cluster-info &> /dev/null; then
        print_error "Cannot connect to Kubernetes cluster"
        exit 1
    fi
    
    print_status "Kubernetes cluster connectivity verified"
}

# Check if manifest files exist
check_manifests() {
    local manifest_dir="k8s-manifests"
    local required_files=(
        "n8n-namespace.yaml"
        "n8n-pvc.yaml"
        "n8n-deployment.yaml"
        "n8n-service.yaml"
    )
    
    if [[ ! -d "$manifest_dir" ]]; then
        print_error "Manifest directory '$manifest_dir' not found"
        exit 1
    fi
    
    for file in "${required_files[@]}"; do
        if [[ ! -f "$manifest_dir/$file" ]]; then
            print_error "Required manifest file '$manifest_dir/$file' not found"
            exit 1
        fi
    done
    
    print_status "All required manifest files found"
}

# Deploy namespace
deploy_namespace() {
    print_header "Deploying namespace..."
    kubectl apply -f k8s-manifests/n8n-namespace.yaml
    
    # Wait for namespace to be ready
    kubectl wait --for=condition=ready namespace/n8n --timeout=30s
    print_status "Namespace deployed successfully"
}

# Deploy persistent volume claim
deploy_pvc() {
    print_header "Deploying persistent volume claim..."
    kubectl apply -f k8s-manifests/n8n-pvc.yaml
    
    # Wait for PVC to be bound
    print_status "Waiting for PVC to be bound..."
    kubectl wait --for=condition=bound pvc/n8n-data -n n8n --timeout=120s
    print_status "PVC deployed and bound successfully"
}

# Generate and deploy secrets
deploy_secrets() {
    print_header "Generating and deploying secrets..."
    
    # Generate encryption key if not exists
    if ! kubectl get secret n8n-secrets -n n8n &> /dev/null; then
        ENCRYPTION_KEY=$(openssl rand -hex 32)
        
        kubectl create secret generic n8n-secrets \
            --from-literal=encryption-key="$ENCRYPTION_KEY" \
            -n n8n
        
        print_status "Secrets generated and deployed"
    else
        print_warning "Secrets already exist, skipping generation"
    fi
}

# Deploy application
deploy_app() {
    print_header "Deploying N8N application..."
    kubectl apply -f k8s-manifests/n8n-deployment.yaml
    
    # Wait for deployment to be ready
    print_status "Waiting for deployment to be ready..."
    kubectl rollout status deployment/n8n -n n8n --timeout=300s
    print_status "Application deployed successfully"
}

# Deploy service
deploy_service() {
    print_header "Deploying service..."
    kubectl apply -f k8s-manifests/n8n-service.yaml
    
    # Wait for endpoints to be ready
    print_status "Waiting for service endpoints..."
    sleep 10
    kubectl get endpoints -n n8n n8n-service
    print_status "Service deployed successfully"
}

# Verify deployment
verify_deployment() {
    print_header "Verifying deployment..."
    
    # Check all resources
    kubectl get all -n n8n
    
    # Check resource usage
    echo ""
    print_status "Resource usage:"
    kubectl top pods -n n8n || print_warning "Metrics not available"
    
    # Test local connectivity
    echo ""
    print_status "Testing local connectivity..."
    NODE_PORT=$(kubectl get svc n8n-service -n n8n -o jsonpath='{.spec.ports[0].nodePort}')
    
    if curl -s -o /dev/null -w "%{http_code}" http://localhost:${NODE_PORT} | grep -q "200"; then
        print_status "Local connectivity test passed"
    else
        print_warning "Local connectivity test failed - service may still be starting"
    fi
    
    echo ""
    print_status "Deployment verification completed"
}

# Display access information
show_access_info() {
    print_header "Access Information"
    
    NODE_PORT=$(kubectl get svc n8n-service -n n8n -o jsonpath='{.spec.ports[0].nodePort}')
    NODE_IPS=$(kubectl get nodes -o jsonpath='{.items[*].status.addresses[?(@.type=="InternalIP")].address}')
    
    echo "Local access URLs:"
    for ip in $NODE_IPS; do
        echo "  http://$ip:$NODE_PORT"
    done
    
    echo ""
    echo "External access (after Cloudflare tunnel setup):"
    echo "  https://n8n.yourdomain.com"
    
    echo ""
    print_warning "Remember to:"
    echo "1. Configure Cloudflare tunnel to point to localhost:$NODE_PORT"
    echo "2. Set up DNS CNAME record in Cloudflare"
    echo "3. Update deployment with your actual domain name"
}

# Cleanup function
cleanup_deployment() {
    print_header "Cleaning up N8N deployment..."
    
    # Delete in reverse order
    kubectl delete -f k8s-manifests/n8n-service.yaml --ignore-not-found
    kubectl delete -f k8s-manifests/n8n-deployment.yaml --ignore-not-found
    kubectl delete secret n8n-secrets -n n8n --ignore-not-found
    kubectl delete -f k8s-manifests/n8n-pvc.yaml --ignore-not-found
    kubectl delete -f k8s-manifests/n8n-namespace.yaml --ignore-not-found
    
    print_status "Cleanup completed"
}

# Main function
main() {
    case "${1:-deploy}" in
        "deploy")
            print_header "Starting N8N deployment to K3s cluster..."
            check_kubectl
            check_manifests
            deploy_namespace
            deploy_pvc
            deploy_secrets
            deploy_app
            deploy_service
            verify_deployment
            show_access_info
            print_status "N8N deployment completed successfully!"
            ;;
        "cleanup")
            cleanup_deployment
            ;;
        "status")
            kubectl get all -n n8n
            ;;
        *)
            echo "Usage: $0 [deploy|cleanup|status]"
            echo "  deploy  - Deploy N8N to cluster (default)"
            echo "  cleanup - Remove N8N deployment"
            echo "  status  - Show deployment status"
            exit 1
            ;;
    esac
}

# Make script executable and run
main "$@"
