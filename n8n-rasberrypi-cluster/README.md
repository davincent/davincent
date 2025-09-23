# Enterprise-Grade Homelab: K3s Cluster with N8N Workflow Automation

A production-ready Kubernetes cluster running on Raspberry Pi hardware, featuring workflow automation, zero-trust networking, and enterprise management tools.

## 🏗️ Architecture Overview

## 🏗️ Architecture Diagram
```mermaid
graph TB
    Internet[Internet Users] --> CF[Cloudflare Network]
    CF --> |Encrypted Tunnel| Home[Home Network]
    
    Home --> K3s[K3s Cluster]
    K3s --> Master[Master Node<br/>Control Plane]
    K3s --> Workers[6x Worker Nodes<br/>28 cores, 26GB RAM]
    
    Workers --> N8N[N8N Application<br/>NodePort: 30080]
    
    Home --> Rancher[Rancher Management<br/>Dedicated Pi]
    Rancher --> |Manages| K3s
    
    CF --> |SSL/TLS| CF
    CF --> |DDoS Protection| CF
    CF --> |DNS Management| CF
