# Cloudflare Tunnel Setup Instructions

## Prerequisites
- Cloudflare account
- Domain registered with Cloudflare
- Cloudflared binary installed

## Step 1: Authentication
```bash
# Get authentication URL
cloudflared tunnel login --url

# Open the URL in browser and complete authentication
# Credentials will be saved to ~/.cloudflared/cert.pem
```
## Step 2: Create Tunnel
```bash
# Create a new tunnel
cloudflared tunnel create n8n-tunnel

# Note the tunnel ID from the output
# Example: Created tunnel n8n-tunnel with id 12345678-90ab-cdef-1234-567890abcdef
```
## Step 3: Configure Tunnel
```bash
# Copy template configuration
sudo mkdir -p /etc/cloudflared
sudo cp cloudflare/config.yml.template /etc/cloudflared/config.yml

# Edit configuration with your details
sudo nano /etc/cloudflared/config.yml

# Update the following values:
# - tunnel: YOUR_TUNNEL_ID
# - credentials-file: /home/USERNAME/.cloudflared/YOUR_TUNNEL_ID.json
# - hostname: n8n.yourdomain.com (replace with your domain)
```
## Step 4: DNS Configuration

1. Log into Cloudflare Dashboard
2. Select your domain
3. Go to DNS → Records
4. Add CNAME record:
- Type: CNAME
- Name: n8n
- Target: YOUR_TUNNEL_ID.cfargotunnel.com
- Proxy status: Proxied (orange cloud)



## Step 5: Test Configuration
```bash
# Validate tunnel configuration
cloudflared tunnel --config /etc/cloudflared/config.yml ingress validate

# Test tunnel manually (optional)
cloudflared tunnel --config /etc/cloudflared/config.yml run
```
## Step 6: Install as Service
```bash
# Install cloudflared as system service
sudo cloudflared service install

# Start and enable service
sudo systemctl start cloudflared
sudo systemctl enable cloudflared

# Check service status
sudo systemctl status cloudflared
```
## Step 7: Verify Access
```bash
# Test local service
curl http://localhost:30080

# Test external access
curl -I https://n8n.yourdomain.com

# Check DNS resolution
nslookup n8n.yourdomain.com
```
## Troubleshooting
### Common Issues
1. 404 Error: Check hostname configuration in config.yml
2. Connection Refused: Verify local service is running on port 30080
3. DNS Issues: Check CNAME record configuration
4. Authentication Errors: Re-run tunnel authentication

### Useful Commands
```bash
# Check tunnel status
cloudflared tunnel list

# View tunnel logs
sudo journalctl -u cloudflared -f

# Restart tunnel service
sudo systemctl restart cloudflared

# Test ingress rules
cloudflared tunnel --config /etc/cloudflared/config.yml ingress rule https://n8n.yourdomain.com
```
## Security Best Practices
- Use strong encryption keys
- Regularly rotate credentials
- Monitor access logs
- Enable Cloudflare security features
- Keep cloudflared updated
