# Enterprise-Grade Homelab: K3s Cluster with N8N Workflow Automation

A production-ready Kubernetes cluster running on Raspberry Pi hardware, featuring workflow automation, zero-trust networking, and enterprise management tools.

## 🏗️ Architecture Overview
### Hardware Layer
- **K3s Cluster**: 7x Raspberry Pi 4 (4GB each)
  - 1x Master Node (Control Plane)
  - 6x Worker Nodes (Workload Scheduling)
- **Management**: 1x Dedicated Pi running Rancher
- **Total Resources**: 28 CPU cores, 26GB RAM

### Software Stack
- **Container Orchestration**: k3s (Lightweight Kubernetes)
- **Application**: n8n workflow automation
- **Networking**: Cloudflare Tunnel (Zero-trust access)
- **Management**: Rancher (Web-based cluster management)
- **Storage**: local-path-provisioner (Persistent volumes)

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

## 🔗 Related Projects

- k3s Documentation
- n8n Documentation
- Cloudflare Tunnel Docs
- Rancher Documentation
