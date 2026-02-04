#!/bin/bash
# Define where to store the generated certs and metadata.
DIR="$(pwd)/.tls"

# Optional: Ensure the target directory exists and is empty.
rm -rf "${DIR}"
mkdir -p "${DIR}"

# Create the openssl configuration file. This is used for both generating
# the certificate as well as for specifying the extensions. It aims in favor
# of automation, so the DN is encoding and not prompted.
cat > "${DIR}/openssl.cnf" << EOF
[req]
default_bits = 2048
encrypt_key  = no # Change to encrypt the private key using des3 or similar
default_md   = sha256
prompt       = no
utf8         = yes

# Specify the DN here so we aren't prompted (along with prompt = no above).
distinguished_name = req_distinguished_name

# Extensions for SAN IP and SAN DNS
req_extensions = v3_req

# Be sure to update the subject to match your organization.
# Different from the subject below, but it doesn't matter.
[req_distinguished_name]
C  = US
ST = California
L  = The Cloud
O  = Demo
CN = github.com-landron

# Allow client and server auth. You may want to only allow server auth.
# Link to SAN names.
[v3_req]
basicConstraints        = critical, CA:FALSE
subjectKeyIdentifier    = hash
# https://github.com/openssl/openssl/issues/22966
# the AKID can not, simply because there is no issuer certificate available, which is correctly indicated by the errors thrown:
# 807BB4E91F7B0000:error:11000079:X509 V3 routines:v2i_AUTHORITY_KEYID:no issuer certificate:../crypto/x509/v3_akid.c:145:
# authorityKeyIdentifier  = keyid:always, issuer:always
keyUsage                = critical, digitalSignature, keyEncipherment
# keyUsage                = critical, nonRepudiation, digitalSignature, keyEncipherment, keyAgreement
extendedKeyUsage        = critical, clientAuth, serverAuth
subjectAltName          = @alt_names

# Alternative names are specified as IP.# and DNS.# for IP addresses and
# DNS accordingly.
[alt_names]
IP.1  = 192.168.14.2
IP.2  = 192.168.14.4
DNS.1 = localhost
EOF

# Create the certificate authority (CA). This will be a self-signed CA, and this
# command generates both the private key and the certificate. You may want to
# adjust the number of bits (4096 is a bit more secure, but not supported in all
# places at the time of this publication).
#
# To put a password on the key, remove the -nodes option.
#
# Be sure to update the subject to match your organization.
openssl req \
  -new \
  -newkey rsa:2048 \
  -days 120 \
  -nodes \
  -x509 \
  -subj "/C=US/ST=California/L=The Cloud/O=github.com-landron-26.01" \
  -keyout "${DIR}/ca.key" \
  -out "${DIR}/ca.crt"
# openssl req -new -newkey rsa:2048 -days 120 -nodes -x509 -subj "/C=US/ST=California/L=The Cloud/O=github.com-landron"

#
# For each server/service you want to secure with your CA, repeat the
# following steps:
#

# Generate the private key for the service. Again, you may want to increase
# the bits to 4096.
openssl genrsa -out "${DIR}/my-service.key" 2048

# Generate a CSR using the configuration and the key just generated. We will
# give this CSR to our CA to sign.
openssl req \
  -new -key "${DIR}/my-service.key" \
  -out "${DIR}/my-service.csr" \
  -config "${DIR}/openssl.cnf"
# openssl req -new -key "my-service.key" -out "my-service.csr" -config "openssl.cnf"

# Sign the CSR with our CA. This will generate a new certificate that is signed
# by our CA.
openssl x509 \
  -req \
  -days 120 \
  -in "${DIR}/my-service.csr" \
  -CA "${DIR}/ca.crt" \
  -CAkey "${DIR}/ca.key" \
  -CAcreateserial \
  -extensions v3_req \
  -extfile "${DIR}/openssl.cnf" \
  -out "${DIR}/my-service.crt"

# (Optional) Verify the certificate.
openssl x509 -in "${DIR}/my-service.crt" -noout -text

# Here is a sample response (truncate):
#
# Certificate:
#     Signature Algorithm: sha256WithRSAEncryption
#         Issuer: C = US, ST = California, L = The Cloud, O = My Organization CA
#         Subject: C = US, ST = California, L = The Cloud, O = Demo, CN = My Certificate
#         # ...
#         X509v3 extensions:
#             X509v3 Basic Constraints:
#                 CA:FALSE
#             X509v3 Subject Key Identifier:
#                 36:7E:F0:3D:93:C6:ED:02:22:A9:3D:FF:18:B6:63:5F:20:52:6E:2E
#             X509v3 Key Usage:
#                 Digital Signature, Key Encipherment
#             X509v3 Extended Key Usage:
#                 TLS Web Client Authentication, TLS Web Server Authentication
#             X509v3 Subject Alternative Name:
#                 IP Address:1.2.3.4, DNS:my.dns.name
#

zip -r ~/certs.zip .tls
var=$(realpath ~/certs.zip)
echo "$var updated."
