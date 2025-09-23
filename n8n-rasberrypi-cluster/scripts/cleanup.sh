#!/bin/bash
# Complete Environment Cleanup Script

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
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

# Cleanup Kubernetes resources
cleanup_k8s() {
    print_status "Cleaning up Kubernetes resources..."
    
    if command -v kubectl &> /dev/null; then
        # Delete N8N namespace and all resources
        kubectl delete namespace n8n --ignore-not-found
        
        # Wait for namespace deletion
        print_status "Waiting for namespace deletion..."
        kubectl wait --for=delete namespace/n8n --timeout=120s &> /dev/null || true
        
        print_status "Kubernetes resources cleaned up"
    else
        print_warning "kubectl not found, skipping Kubernetes cleanup"
    fi
}

# Cleanup Cloudflare tunnel
cleanup_cloudflare() {
    print_status "Cleaning up Cloudflare tunnel..."
    
    # Stop and disable service
    sudo systemctl stop cloudflared 2>/dev/null || true
    sudo systemctl disable cloudflared 2>/dev/null || true
    
    # Uninstall service
    sudo cloudflared service uninstall 2>/dev/null || true
    
    # Remove service files
    sudo rm -f /etc/systemd/system/cloudflared*.service
    sudo rm -f /lib/systemd/system/cloudflared*.service
    
    # Remove configuration
    sudo rm -rf /etc/cloudflared/
    rm -rf ~/.cloudflared/
    sudo rm -rf /root/.cloudflared/
    
    # Remove binary
    sudo rm -f /usr/local/bin/cloudflared
    sudo rm -f /usr/bin/cloudflared
    
    # Reload systemd
    sudo systemctl daemon-reload
    
    # Kill any remaining processes
    sudo pkill -9 cloudflared 2>/dev/null || true
    
    print_status "Cloudflare tunnel cleaned up"
}

# Cleanup container images
cleanup_images() {
    print_status "Cleaning up container images..."
    
    if command -v k3s &> /dev/null; then
        # Remove N8N images
        sudo k3s crictl rmi docker.io/n8nio/n8n:latest 2>/dev/null || true
        
        # Prune unused images
        sudo k3s crictl rmi --prune 2>/dev/null || true
        
        print_status "Container images cleaned up"
    else
        print_warning "k3s not found, skipping image cleanup"
    fi
}

# Cleanup logs
cleanup_logs() {
    print_status "Cleaning up logs..."
    
    # Clean systemd logs
    sudo journalctl --vacuum-time=1d 2>/dev/null || true
    
    # Clean container logs
    sudo find /var/log -name "*.log" -type f -mtime +7 -delete 2>/dev/null || true
    
    print_status "Logs cleaned up"
}

# Cleanup temporary files
cleanup_temp() {
    print_status "Cleaning up temporary files..."
    
    # Clean temp directories
    sudo rm -rf /tmp/cloudflared* 2>/dev/null || true
    sudo rm -rf /tmp/k8s-* 2>/dev/null || true
    
    # Clean package caches
    sudo apt autoremove -y 2>/dev/null || true
    sudo apt autoclean 2>/dev/null || true
    
    print_status "Temporary files cleaned up"
}

# Verification
verify_cleanup() {
    print_status "Verifying cleanup..."
    
    echo "Checking for remaining processes:"
    ps aux | grep -E "(cloudflared|n8n)" | grep -v grep || echo "  No remaining# Homelab K3s N8N Repository Structure
