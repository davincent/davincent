# Enterprise-Grade Homelab: K3s Cluster with N8N Workflow Automation

A production-ready Kubernetes cluster running on Raspberry Pi hardware, featuring workflow automation, zero-trust networking, and enterprise management tools.

## 🏗️ Architecture Overview

## 🏗️ Architecture Diagram
```mermaid
graph TD
    Users[External Users] --> CF[Cloudflare Network]
    
    subgraph "Cloudflare Services"
        CF --> DNS[DNS Management]
        CF --> SSL[SSL/TLS Termination]
        CF --> DDoS[DDoS Protection]
    end
    
    CF --> |Encrypted Tunnel| Tunnel[Cloudflare Tunnel]
    
    subgraph "Home Network"
        Tunnel --> |Port 30080| K3sCluster[K3s Cluster]
        
        subgraph "K3s Cluster - 7 Raspberry Pis"
            direction TB
            Master[Master Node<br/>Control Plane<br/>API Server] 
            Workers[6x Worker Nodes<br/>28 CPU Cores<br/>26GB RAM]
            Master -.->|Schedules| Workers
        end
        
        subgraph "Applications"
            N8N[N8N Workflow Engine<br/>2-8GB RAM<br/>1-4 CPU Cores<br/>20GB Storage]
        end
        
        Workers --> N8N
        
        RancherPi[Rancher Management<br/>Dedicated Pi] -.->|Manages| K3sCluster
    end
    
    style CF fill:#f39c12
    style K3sCluster fill:#3498db
    style N8N fill:#2ecc71
    style RancherPi fill:#9b59b6
