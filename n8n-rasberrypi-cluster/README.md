# Enterprise-Grade Homelab: K3s Cluster with N8N Workflow Automation

A production-ready Kubernetes cluster running on Raspberry Pi hardware, featuring workflow automation, zero-trust networking, and enterprise management tools.

## 🏗️ Architecture Overview

┌─────────────────┐    ┌──────────────────────────┐    ┌─────────────────┐
│   Cloudflare    │    │     K3s Cluster (7 Pis)  │    │   Rancher Mgmt  │
│   DNS & Tunnel  │────│  ┌─────┬─────┬─────┐     │────│   (1 Pi)        │
│                 │    │  │ CP1 │ CP2 │ CP3 │     │    │                 │
└─────────────────┘    │  └─────┴─────┴─────┘     │    └─────────────────┘
│  ┌─────┬─────┬─────┐     │
│  │ W1  │ W2  │ W3  │     │
│  └─────┴─────┴─────┘     │
│  ┌─────┐               │
│  │ W4  │               │
│  └─────┘               │
└──────────────────────────┘
