import rsa
from vigenere import encrypt, decrypt, random_key



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
    print(f"Private Key: {private_key}\n")
    print(f"Public Key: {public_key}\n")
    print(f"Cipher Key: {cipher_key}\n")
    return public_key, private_key, cipher_key


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



def encrypted(public_key, vignere_key,private_key):
    message = input("Enter the message to be encrypted: ")
    # message = rsa.encrypt(message.encode('ascii'), public_key)
    # print(f"{message}\n")

    message = encrypt(message, vignere_key) # with random_key function, cipher may vary everytime you run a program.
    print(f"{message}")
    message = rsa.encrypt(message.encode('ascii'), public_key)
    print(f"{message}\n")
    decrypted_val = rsa.decrypt(message, public_key).decode('ascii')
    decrypted_val = decrypt(decrypted_val, vignere_key)
    print(f"{decrypted_val}")
    # cipher =decrypt(message, vignere_key)   
    # print(f"{cipher}")
    # return message



def decrypted(ciphertext, key):
    try:
        cipher = decrypt(cipher, vignere_key)
        return rsa.decrypt(ciphertext, key).decode('ascii')
    except:
        return False





if __name__ == '__main__':
    # CHOICE = 0
    # while CHOICE != 4:
    #     print("----------Mai Cipher----------")
    #     print("Encrypt______________________1")
    #     print("Decrypt______________________2")
    #     print("Generate Keys________________3")
    #     print("Exit_________________________5")
    #     CHOICE = input("Enter your choice: ")

    #     if CHOICE  == '1':
    #          encrypted(public_key,vignere_key,private_key)
    #     elif CHOICE == '2':
    #         print("Input 2")
    #     elif CHOICE == '3':
    #         generate_keys()
    #         (private_key, public_key, vignere_key) = load_keys()
    #     elif CHOICE == '4':
    #         break
    #     else:
    #         print("Wrong Input")