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
