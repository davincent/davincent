# Enterprise-Grade Homelab: K3s Cluster with N8N Workflow Automation

A production-ready Kubernetes cluster running on Raspberry Pi hardware, featuring workflow automation, zero-trust networking, and enterprise management tools.

## 🏗️ Architecture Overview

[Users] → [Cloudflare DNS] → [Cloudflare Tunnel] → [Home Network] → [K3s NodePort] → [N8N Pod]
   ↓              ↓                    ↓               ↓              ↓             ↓
Internet    SSL/DDoS/CDN    Encrypted Tunnel    Pi Cluster    Service Mesh    Application
