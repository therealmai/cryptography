import rsa
from vigenere import encrypt, decrypt, random_key
from string import ascii_letters, digits
from random import shuffle

monoalpha_cipher = {'a': 'm', 'b': 'n', 'c': 'b', 'd': 'v', 'e': 'c', 'f': 'x','g': 'z', 'h': 'a', 'i': 's', 'j': 'd', 'k': 'f',
                    'l': 'g', 'm': 'h', 'n': 'j', 'o': 'k', 'p': 'l', 'q': 'p', 'r': 'o', 's': 'i', 't': 'u', 'u': 'y', 'v': 't', 'w': 'r', 'x': 'e', 'y': 'w', 
                    'z': 'q', ' ': ' ',
}

def encrypt_with_monoalpha(message, monoalpha_cipher):
   encrypted_message = []
   for letter in message:
      encrypted_message.append(monoalpha_cipher.get(letter, letter))
   return ''.join(encrypted_message)


def decrypt_with_monoalpha(encrypted_message, monoalpha_cipher):
   return encrypt_with_monoalpha(
      encrypted_message,
      inverse_monoalpha_cipher(monoalpha_cipher)
   )

def inverse_monoalpha_cipher(monoalpha_cipher):
   inverse_monoalpha = {}
   for key, value in monoalpha_cipher.items():
      inverse_monoalpha[value] = key
   return inverse_monoalpha


def random_monoalpha_cipher(pool = None):
   if pool is None:
      pool = ascii_letters + digits
   original_pool = list(pool)
   shuffled_pool = list(pool)
   shuffle(shuffled_pool)
   return dict(zip(original_pool, shuffled_pool))


def generate_keys():
    (publicKey, privateKey) = rsa.newkeys(1024)
    with open('keys/publcKey.pem', 'wb') as p:
        p.write(publicKey.save_pkcs1('PEM'))
    with open('keys/privateKey.pem', 'wb') as p:
        p.write(privateKey.save_pkcs1('PEM'))
    print("\nKeys are generated in ./keys/\n")


def load_keys():
    with open('keys/publcKey.pem', 'rb') as p:
        public_key = rsa.PublicKey.load_pkcs1(p.read())
    with open('keys/privateKey.pem', 'rb') as p:
        private_key = rsa.PrivateKey.load_pkcs1(p.read())
    cipher_key:str = random_key()
    mono_cipher = random_monoalpha_cipher()
    return public_key, private_key, cipher_key, mono_cipher


def atbash(plain):
    n = len (plain)
    crypt = ''
    for i in range ( 0, n ):
        ival = ord ( plain[i] )
        if ( ord ( 'a' ) <= ival and ival <= ord ( 'z' ) ):
            jval = ord ( 'a' ) + ord ( 'z' ) - ival
            crypt = crypt + chr ( jval )
        elif ( ord ( 'A' ) <= ival and ival <= ord ( 'Z' ) ):
            jval = ord ( 'A' ) + ord ( 'Z' ) - ival
            crypt = crypt + chr ( jval )
        else:
            crypt = crypt + plain[i]
    return crypt


def encrypted(rsa_key, vignere_key, mono_key):
    message = input("Enter the message to be encrypted: ")
    filename = input("Enter Filename:")

    cipher_text = encrypt(message, vignere_key)
    cipher_text = atbash(cipher_text)
    cipher_text = encrypt_with_monoalpha(cipher_text, mono_key)
    cipher_text = rsa.encrypt(cipher_text.encode('ascii'), rsa_key)

    # Open File and Write Ciphertext into binary File
    _fp = open(filename, 'wb')
    if(_fp.writable() and _fp is not None) :
        _fp.write(cipher_text)
        print(f'Plain Text: {message}')
        print(f'Mai Cipher: {cipher_text}')
    else:
        print("Error in Writing")
    _fp.close()



def decrypted(rsa_key, vignere_key, mono_key):
    filename = input("Enter Filename: ")

    #Open File and Read Ciphertext and Decrypt
    _fp = open(filename, 'rb')
    if _fp is not None :
        encrypted_text = _fp.read()
        decrypted_val = rsa.decrypt(encrypted_text, rsa_key).decode('ascii')
        decrypted_val = decrypt_with_monoalpha(decrypted_val, mono_key)
        decrypted_val = atbash(decrypted_val)
        decrypted_val = decrypt(decrypted_val, vignere_key)
        print(f'Encrypted Text: {encrypted_text}')
        print(f'Mai Cipher: {decrypted_val}')
    else :
        print("Error in Reading")
    _fp.close()


if __name__ == '__main__':
    PUBLIC_KEY = ''
    VIGNERE_KEY = ''
    PRIVATE_KEY = ''
    MONO_CIPHER_KEY = ''
    CHOICE = 0
    while CHOICE != 4:
        print("----------Mai Cipher----------")
        print("Encrypt______________________1")
        print("Decrypt______________________2")
        print("Generate Keys________________3")
        print("Exit_________________________4")
        CHOICE = input("Enter your choice: ")

        if CHOICE  == '1':
            encrypted(PUBLIC_KEY, VIGNERE_KEY, MONO_CIPHER_KEY)
        elif CHOICE == '2':
            decrypted(PUBLIC_KEY, VIGNERE_KEY, MONO_CIPHER_KEY)
        elif CHOICE == '3':
            generate_keys()
            (PRIVATE_KEY, PUBLIC_KEY, VIGNERE_KEY,MONO_CIPHER_KEY) = load_keys()
        elif CHOICE == '4':
            break
        else:
            print("Wrong Input")