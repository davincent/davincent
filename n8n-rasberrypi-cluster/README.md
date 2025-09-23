# Enterprise-Grade Homelab: K3s Cluster with N8N Workflow Automation

A production-ready Kubernetes cluster running on Raspberry Pi hardware, featuring workflow automation, zero-trust networking, and enterprise management tools.

## 🏗️ Architecture Overview

## 🏗️ Architecture Diagram
```mermaid
graph TD
    Users[External Users]
    Users --> CF[Cloudflare Network]
    CF --> Tunnel[Encrypted Tunnel]
    Tunnel --> Home[Home Network]
    
    Home --> K3s[K3s Cluster]
    
    subgraph "Infrastructure"
        Master[Master Node<br/>Control Plane]
        Workers[6x Worker Nodes<br/>28 Cores, 26GB RAM]
        N8N[N8N Application<br/>Workflow Engine]
        Rancher[Rancher Management<br/>Dedicated Pi]
    end
    
    K3s --> Master
    Master --> Workers
    Workers --> N8N
    Home --> Rancher
    Rancher -.-> K3s
    
    style CF fill:#f39c12
    style N8N fill:#2ecc71
    style Rancher fill:#9b59b6
