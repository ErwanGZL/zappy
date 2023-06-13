import zlib
import base64


"""
XOR cipher algorithm
Permet de chiffrer un message avec une clé
"""


def xor_cipher(message, key):
    encrypted_message = ""
    key_length = len(key)
    for i, char in enumerate(message):
        key_char = key[i % key_length]
        encrypted_char = chr(ord(char) ^ ord(key_char))
        encrypted_message += encrypted_char
    return encrypted_message


def xor_compressed_cipher(message, key):
    compressed_message = zlib.compress(message.encode())
    compressed_message_b64 = base64.b64encode(compressed_message).decode()
    encrypted_message = xor_cipher(compressed_message_b64, key)
    return encrypted_message


def xor_compressed_decipher(encrypted_message, key):
    decrypted_message = xor_cipher(encrypted_message, key)
    compressed_message = base64.b64decode(decrypted_message)
    decompressed_message = zlib.decompress(compressed_message).decode()
    return decompressed_message


def str_to_list(content: str):
    content = content.split(",")
    result = []
    for item in content:
        parts = item.split(" ")
        name = parts[0]
        value = parts[1]
        result.append((name, value))
    return result
