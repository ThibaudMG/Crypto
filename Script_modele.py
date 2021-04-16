import codecs
import ecdsa
from Crypto.Hash import keccak
import random

# Definition private key
private_key_hex = hex(random.getrandbits(256))[2:] # Remove '0x'

# Fonctions
def initialize(private_key_hex):
  global private_key; global public_key

  private_key_bytes = bytes.fromhex(private_key_hex) # Hex to Bytes

  key = ecdsa.SigningKey.from_string(private_key_bytes, curve=ecdsa.SECP256k1).verifying_key # The public key is a point on the secp256k1 ECDSA curve (x,y point)
  key_bytes = key.to_string()
  private_key = codecs.encode(private_key_bytes, 'hex') # Bytes to Hex
  public_key = codecs.encode(key_bytes, 'hex') # Bytes to Hex

def get_private_key():
  return private_key

def get_public_key():
  return public_key

#########

initialize(private_key_hex)

print("Private key: ", get_private_key())
print("Public key: ", get_public_key())


public_key_bytes = codecs.decode(public_key, 'hex')

# Public key is then hashed using Keccak-256 (aka SHA-3), and the lower 160 bits becomes the public Ethereum address

hash = keccak.new(digest_bits=256)
hash.update(public_key_bytes)
keccak_digest = hash.hexdigest()

address = '0x' + keccak_digest[-40:]
print("Address: ",address)
