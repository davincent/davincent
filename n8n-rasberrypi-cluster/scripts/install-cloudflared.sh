#!/bin/bash
# Cloudflared Installation Script for ARM64 (Raspberry Pi)

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if running on ARM64
check_architecture() {
    ARCH=$(uname -m)
    if [[ "$ARCH" != "aarch64" ]]; then
        print_error "This script is designed for ARM64 architecture. Detected: $ARCH"
        exit 1
    fi
    print_status "Architecture check passed: $ARCH"
}

# Download and install cloudflared
install_cloudflared() {
    print_status "Downloading cloudflared for ARM64..."
    
    # Create temporary directory
    TEMP_DIR=$(mktemp -d)
    cd "$TEMP_DIR"
    
    # Download latest release
    wget https://github.com/cloudflare/cloudflared/releases/latest/download/cloudflared-linux-arm64
    
    # Verify download
    if [[ ! -f "cloudflared-linux-arm64" ]]; then
        print_error "Failed to download cloudflared"
        exit 1
    fi
    
    # Make executable
    chmod +x cloudflared-linux-arm64
    
    # Install to system directory
    print_status "Installing cloudflared to /usr/local/bin..."
    sudo mv cloudflared-linux-arm64 /usr/local/bin/cloudflared
    
    # Cleanup
    cd /
    rm -rf "$TEMP_DIR"
    
    print_status "Cloudflared installed successfully"
}

# Verify installation
verify_installation() {
    print_status "Verifying installation..."
    
    if command -v cloudflared &> /dev/null; then
        VERSION=$(cloudflared --version)
        print_status "Cloudflared version: $VERSION"
    else
        print_error "Cloudflared installation failed"
        exit 1
    fi
}

# Create configuration directory
create_config_dir() {
    print_status "Creating configuration directory..."
    
    # Create user config directory
    mkdir -p ~/.cloudflared
    
    # Create system config directory (if it doesn't exist)
    sudo mkdir -p /etc/cloudflared
    
    print_status "Configuration directories created"
}

# Main execution
main() {
    print_status "Starting cloudflared installation..."
    
    check_architecture
    install_cloudflared
    verify_installation
    create_config_dir
    
    print_status "Installation completed successfully!"
    print_warning "Next steps:"
    echo "1. Authenticate with Cloudflare: cloudflared tunnel login --url"
    echo "2. Create a tunnel: cloudflared tunnel create n8n-tunnel"
    echo "3. Configure tunnel: sudo nano /etc/cloudflared/config.yml"
    echo "4. Install as service: sudo cloudflared service install"
}

# Run main function
main "$@"
