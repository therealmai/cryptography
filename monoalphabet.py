from string import ascii_letters, digits
from random import shuffle


monoalpha_cipher = {'a': 'm', 'b': 'n', 'c': 'b', 'd': 'v', 'e': 'c', 'f': 'x','g': 'z', 'h': 'a', 'i': 's', 'j': 'd', 'k': 'f',
                    'l': 'g', 'm': 'h', 'n': 'j', 'o': 'k', 'p': 'l', 'q': 'p', 'r': 'o', 's': 'i', 't': 'u', 'u': 'y', 'v': 't', 'w': 'r', 'x': 'e', 'y': 'w', 
                    'z': 'q', ' ': ' ',
}


def decrypt_with_monoalpha(encrypted_message, monoalpha_cipher):
   return encrypt_with_monoalpha(
      encrypted_message,
      inverse_monoalpha_cipher(monoalpha_cipher)
   )


def encrypt_with_monoalpha(message, monoalpha_cipher):
   encrypted_message = []
   for letter in message:
      encrypted_message.append(monoalpha_cipher.get(letter, letter))
   return ''.join(encrypted_message)


def inverse_monoalpha_cipher(monoalpha_cipher):
   inverse_monoalpha = {}
   for key, value in monoalpha_cipher.iteritems():
      inverse_monoalpha[value] = key
   return inverse_monoalpha


def random_monoalpha_cipher(pool = None):
   if pool is None:
      pool = ascii_letters + digits
   original_pool = list(pool)
   shuffled_pool = list(pool)
   shuffle(shuffled_pool)
   return dict(zip(original_pool, shuffled_pool))