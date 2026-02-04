############################
Favorites

If you need just some keys (not CA):
openssl req -x509 -newkey rsa:2048 -keyout myservice.key -out myservice.cert -days 365 -nodes -subj "/CN=myservice.example.com"
  openssl req -x509 -newkey rsa:2048 -keyout logout.key -out logout.cert -days 365 -nodes -subj "/CN=my-service.saml-tools.com"
  signature/encryption certificates for SAML

$ openssl verify -verbose -x509_strict -CAfile tls/ca.crt tls/my-service.crt
tls/my-service.crt: OK

$ file tls/ca.crt
tls/ca.crt: PEM certificate
These crt files are PEM.

############################
PKCS#8 to PKCS#1

openssl req -x509 -newkey rsa:2048 -keyout private.pem -out public.pem -days 3650 -nodes -subj "/CN=bas.saml.test"
  PEM: -----BEGIN PRIVATE KEY-----
  ParsePKCS8PrivateKey
  newer PKCS#8 format, PKCS#8 is a more general format and can be used for various key types

openssl pkey -in private.pem -out private_rsa.pem -traditional
  PEM: -----BEGIN RSA PRIVATE KEY-----
  ParsePKCS1PrivateKey
  older PKCS#1 format

############################
Knowledge base

##############
Generate CA
  Be sure to update -subj "/C=US/ST=California/L=The Cloud/O=github.com-landron-26.01" to differentiate certificates

Add CA to OS
  # Alternative names are specified as IP.# and DNS.# for IP addresses and
  # DNS accordingly.
  [alt_names]
  IP.1  = 192.168.14.2
  DNS.1 = localhost

wget https://localhost:8081/hello-world
  much better log
curl https://localhost:8081/hello-world
curl -li https://localhost:8081/hello-world

install CA certificate
$ openssl x509 -noout -fingerprint -in tls/ca.crt
SHA1 Fingerprint=48:A8:43:9B:11:5B:01:DE:C5:DD:4B:2E:23:0F:DE:7B:D1:9F:7F:B8
  in Chrome is named Thumbprint

Centos:
  - /etc/pki/ca-trust/source/anchors/
  - update-ca-trust
    /etc/pki/ca-trust/extracted/pem/tls-ca-bundle.pem

  cp tls/ca.crt /etc/pki/ca-trust/source/anchors/ca-test.pem
  update-ca-trust
  openssl verify -verbose -x509_strict tls/my-service.crt

  rm /etc/pki/ca-trust/source/anchors/ca-test.pem
  update-ca-trust

Ubuntu
  cp tls/ca.crt /usr/local/share/ca-certificates/ca-dev.crt
  update-ca-certificates --fresh
    openssl verify -verbose tls/my-service.crt
      openssl verify -verbose -x509_strict tls/my-service.crt
      error 92 at 1 depth lookup: CA cert does not include key usage extension
  cp tls/my-service.* <base path>.local/tls/site

Windows:
  certmgr.msc
    Trusted Root Certification Authorities / Certificates
    https://www.techrepublic.com/article/how-to-add-a-trusted-certificate-authority-certificate-to-chrome-and-firefox/

    Trusted Root Certificates is important!

############################
Reference

Use openssl to create an x509 self-signed certificate authority (CA), certificate signing request (CSR), and resulting private key with IP SAN and DNS SAN
https://gist.github.com/sethvargo/81227d2316207b7bd110df328d83fad8
sethvargo/create-certs.sh

SAN Subject Alternate Name
A SAN or subject alternative name is a structured way to indicate all of the
domain names and IP addresses that are secured by the certificate.

############################
TODO

##############
* error 92 at 1 depth lookup: CA cert does not include key usage extension
$ openssl version
OpenSSL 3.0.2 15 Mar 2022

No: openssl verify -verbose -x509_strict tls/my-service.crt
error 92 at 1 depth lookup: CA cert does not include key usage extension
  Hint: https://www.openssl.org/docs/manmaster/man5/x509v3_config.html

Yes: openssl verify -verbose tls/my-service.crt
