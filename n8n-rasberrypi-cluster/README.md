# Enterprise-Grade Homelab: K3s Cluster with N8N Workflow Automation
A production-ready Kubernetes cluster running on Raspberry Pi hardware, featuring workflow automation, zero-trust networking, and enterprise management tools.

## 🏗️ Architecture Overview
### Hardware Layer
- **K3s Cluster**: 7x Raspberry Pi 4 (4GB each)
  - 1x Master Node (Control Plane)
  - 6x Worker Nodes (Workload Scheduling)
- **Management**: 1x Dedicated Pi running Rancher
- **Total Resources**: 28 CPU cores, 26GB RAM

## 🛠️ Technology Stack

| Component | Technology | Purpose |
|-----------|------------|---------|
| **Orchestration** | k3s (Lightweight Kubernetes) | Container orchestration |
| **Management** | Rancher | Cluster management & monitoring |
| **Application** | n8n | Workflow automation platform |
| **Networking** | Cloudflare Tunnels | Secure external access |
| **DNS** | Cloudflare DNS | Domain management |
| **Storage** | local-path-provisioner | Persistent storage |
| **Runtime** | containerd | Container runtime |
| **OS** | Raspberry OS Lite | Minimal Linux distribution |
### Network Flow
- External Request → Cloudflare → Tunnel → NodePort:30080 → N8N Pod

## 🏗️ Architecture Diagram
<img width="841" height="1225" alt="image" src="https://github.com/user-attachments/assets/8cba5e63-aa1e-4136-9f3c-81bf7df996b3" />

## 📊 Infrastructure Specifications

- **Compute**: 8x Raspberry Pi 4 (4GB RAM each)
- **Cluster Resources**: 28 CPU cores, 26GB RAM across 7 nodes
- **Management**: Dedicated Rancher instance on 8th Pi
- **Storage**: Local-path provisioner with persistent volumes
- **Networking**: Cloudflare tunnel with zero-trust access
- **Container Runtime**: containerd via k3s

## 🛠️ Technology Stack

| Component | Technology | Purpose |
|-----------|------------|---------|
| **Orchestration** | k3s (Lightweight Kubernetes) | Container orchestration |
| **Management** | Rancher | Cluster management & monitoring |
| **Application** | n8n | Workflow automation platform |
| **Networking** | Cloudflare Tunnels | Secure external access |
| **DNS** | Cloudflare DNS | Domain management |
| **Storage** | local-path-provisioner | Persistent storage |
| **Runtime** | containerd | Container runtime |
| **OS** | Raspberry OS Lite | Minimal Linux distribution |

## 🚀 Quick Start

### Prerequisites
- 7+ Raspberry Pi 4 devices with Raspberry OS Lite
- Cloudflare account with domain
- Basic Kubernetes knowledge

### 1. Deploy K3s Cluster
```bash
# Clone repository
git clone https://github.com/yourusername/homelab-k3s-n8n.git
cd homelab-k3s-n8n

# Install k3s on master node
curl -sfL https://get.k3s.io | sh -

# Join worker nodes (run on each worker)
curl -sfL https://get.k3s.io | K3S_URL=https://master-ip:6443 K3S_TOKEN=node-token sh -
```

### 2. Deploy N8N
```bash
# Apply Kubernetes manifests
kubectl apply -f k8s-manifests/

# Verify deployment
kubectl get pods -n n8n
```

### 3. Configure Cloudflare Tunnel
```bash
# Install cloudflared
./scripts/install-cloudflared.sh

# Configure tunnel (follow prompts)
./scripts/setup-tunnel.sh
```

### 4. Access Application
Navigate to https://your-domain.com to access n8n interface.

## 💡 Key Features
### High Availability

- Multi-node cluster with automatic failover
- Persistent storage for data durability
- Health checks and automatic restarts

### Security

- Zero-trust network access via Cloudflare
- No exposed ports on home network
- SSL/TLS termination at edge

### Scalability

- Horizontal scaling ready infrastructure
- Resource limits and requests configured
- Easy addition of new worker nodes

### Operations

- Centralized management via Rancher
- Automated deployments via scripts
- Comprehensive monitoring and logging

### Auto-scaling (Future Enhancement)
- Horizontal Pod Autoscaler configuration
- Vertical Pod Autoscaler for optimal resource usage
- Cluster autoscaler for node management

## 🛡️ Security Considerations
- Network Isolation: No direct internet exposure
- Zero Trust: All access via authenticated tunnels
- Encryption: End-to-end SSL/TLS encryption
- Access Control: Kubernetes RBAC implementation
- Secret Management: Kubernetes secrets for sensitive data

## 📚 Learning Outcomes
### This project demonstrates proficiency in:
- Container Orchestration: Kubernetes administration and YAML manifest creation
- Infrastructure as Code: Declarative infrastructure management
- Network Security: Zero-trust networking principles
- System Administration: Linux system management and troubleshooting
- Cloud Integration: Hybrid cloud networking and DNS management
- Automation: Scripting and deployment automation
- Monitoring: Resource monitoring and performance optimization

## 🔗 Related Projects
- [k3s Documentation](https://k3s.io/)
- [n8n Documentation](https://docs.n8n.io/)
- [Cloudflare Tunnel Docs](https://developers.cloudflare.com/cloudflare-one/connections/connect-apps/)
- [Rancher Documentation](https://rancher.com/docs/)
