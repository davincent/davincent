<img src="https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/kubernetes.svg" title="Kubernetes" alt="Kubernetes" width="50" height="50"/>&nbsp;
<img src="https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/docker.svg" title="Docker" alt="Docker" width="50" height="50"/>&nbsp;
<img src="https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/raspberrypi.svg" title="Raspberry Pi" alt="Raspberry Pi" width="50" height="50"/>&nbsp;
<svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 100 100"><path fill="#EA4B71" fill-rule="evenodd" d="M100 35c0 5.52-4.592 10-10.258 10-4.775 0-8.792-3.187-9.934-7.5H65.492c-2.509 0-4.646 1.767-5.059 4.18l-.42 2.466A9.92 9.92 0 0 1 56.679 50a9.92 9.92 0 0 1 3.334 5.854l.416 2.467a5.09 5.09 0 0 0 5.067 4.179h4.062c1.138-4.312 5.154-7.5 9.934-7.5 5.666 0 10.254 4.48 10.254 10S85.15 75 79.492 75c-4.78 0-8.792-3.187-9.934-7.5h-4.062c-5.017 0-9.292-3.533-10.117-8.354l-.42-2.467A5.09 5.09 0 0 0 49.9 52.5h-4.192c-1.283 4.1-5.191 7.083-9.816 7.083S27.358 56.6 26.079 52.5h-6.008c-1.283 4.1-5.192 7.083-9.813 7.083-5.666 0-10.258-4.479-10.258-10 0-5.52 4.592-10 10.258-10 4.93 0 9.05 3.396 10.034 7.917h5.57c.984-4.52 5.105-7.917 10.034-7.917 4.933 0 9.05 3.396 10.033 7.917h3.967c2.504 0 4.646-1.767 5.054-4.18l.425-2.466c.825-4.82 5.104-8.354 10.117-8.354h14.316c1.142-4.312 5.159-7.5 9.934-7.5C95.408 25 100 29.48 100 35m-5.125 0c0 2.763-2.3 5-5.133 5s-5.125-2.237-5.125-5 2.291-5 5.125-5 5.129 2.237 5.129 5zm-84.62 19.583c2.832 0 5.124-2.237 5.124-5s-2.291-5-5.125-5-5.129 2.238-5.129 5 2.296 5 5.13 5m25.637 0c2.833 0 5.129-2.237 5.129-5s-2.292-5-5.125-5-5.13 2.238-5.13 5 2.292 5 5.126 5M79.483 70c2.834 0 5.125-2.237 5.125-5s-2.291-5-5.125-5-5.125 2.237-5.125 5 2.292 5 5.125 5" clip-rule="evenodd"/></svg>
<img src="https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/linux.svg" title="Linux" alt="Linux" width="50" height="50"/>&nbsp;
<img src="https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/cloudflare.svg" title="Cloudflare" alt="Cloudflare" width="50" height="50"/>&nbsp;
<img src="https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/rancher.svg" title="Rancher" alt="Rancher" width="50" height="50"/>&nbsp;
<img src="https://cdn.jsdelivr.net/npm/simple-icons@v9/icons/gnubash.svg" title="Bash" alt="Bash" width="50" height="50"/>

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
