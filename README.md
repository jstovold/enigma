Enigma
======
A simple straightforward crypto tool emulating the famous Enigma machine.

### License
This software and its source code are distributed under the MIT license.

### Author
Developed by Petr Mánek, Charles University in Prague in 2014.

### See also
Here are few interesting articles I used when developing this software:

* [Enigma machine](http://en.wikipedia.org/wiki/Enigma_machine)
* [Rotor and reflector wiring](http://en.wikipedia.org/wiki/Enigma_rotor_details)
* [Bombe attack](http://en.wikipedia.org/wiki/Bombe)

## Documentation
Usage: `enigma [parameters: -e|-d|-c|-h] [configuration: -r|-rf|-p|-ic|-ec|-gc] [flags: -s|-a]`
 
### Parameters
- `-e --encrypt` encrypts data from stdin, the ciphertext is dumped into stdout
- `-d --decrypt` decrypts ciphertext from stdin, the data is dumped into stdout 
- `-c --crack` attempts to crack the code with brute force, the configuration section is used as a pool of choices on which to base the attack. Assumes the code is successfully cracked, when a regex provided as a value for this parameter matches at least one group in the message.
- `-h --help` displays this message
 
### Configuration
- `-r --rotors` sets rotors in visible order (as seen on the physical machine, electrical current enters and exits the last rotor)

        Rotors can be specified by:
        1) Rotor name, all recognized rotor names are:
                        - c1, c2, c3, (Commercial Enigma A, B - 1924)
                        - gr1, gr2, gr3, (German Railway, Rocket - 1941)
                        - k1, k2, k3, (Swiss K - 1939)
                        - w1, w2, w3, w4, w5, w6, w7, w8, (military rotors - 1930-1939)
                        - w_beta, w_gamma (military rotors - 1940-1942)
 
        2) Explicit rotor wiring (any permutation of 26 alphabetic letters ABCDEFGHIJKLMNOPQRSTUVWXYZ without fixed point)
 
        Additional:
            - to set turnover points, add indices 0-25 and / before the wiring (named rotors have turnover points already set up)
              (index n means that when the rotor is stepping from n to n+1, turnover will occur)
              e.g. 8/12/18/FKQHTLXOCBJSPDZRAMEWNIUYGV
 
            - to specify a starting offset, add : and index 0-25 after the name or wiring
              (starting offset 0 means "as-is")
              e.g. c1:23, FKQHTLXOCBJSPDZRAMEWNIUYGV:17
 
            - default turnover points are none (unless you're using a named rotor), default starting offset is 0
 
            - you can specify as many rotors as you like, but keep in mind that a lot of them might slow down the encryption/decryption process
 
            - separate all rotors by a comma without space
 
        Example usage: -r w8:19,k3,1/8/19/FKQHTLXOCBJSPDZRAMEWNIUYGV:3
 
* `-rf --reflector` sets the reflector
 
        Reflector can be specified by:
        1) Reflector name, all recognized reflector names are:
                        - gr_ukw (German Railway, Rocket - 1941),
                        - k_ukw (Swiss K - 1939)
                        - w_ra, w_rb, w_rc (military rotors - 1930-1942)
                        - w_rbt, w_rct (thin versions of military rotors B and C)
 
        2) Explicit reflector wiring (same as with rotors, but the permutation has to be involution = inverse to itself)
            Here are few examples of what's a valid reflector wiring (only 4 letters are used for clarity)
            e.g. ABCD is valid, DBCA is valid, ACBD is valid, CBAD is valid, BCDA is invalid
 
        Additional:
            - similarly to rotors, you can specify offset of a reflector by adding : and index 0-25
              e.g. w_ra:21, YRUHQSLDPXNGOKMIEBFZCWVJAT:6
 
            - unlike rotors, the reflector does not change offset during the encryption/decryption process
 
* `-p --plugs` configures the plugboard
 
		Plugboard swaps pairs of letters as they enter the rotor assembly, these letters are separated by commas (without spaces), and cannot repeat.
        e.g. AD,PL,FY
 
        Additional:
            - since the swap occurs bidirectionally, the order of the letters doesn't matter (AD = DA, what's more AD,PL = PL,AD)
 
* `-ec --export-config` dumps current configuration into a specified file
* `-ic --import-config` reads configuration from specified file
* `-gc --gen-config` generates random secure configuration (7 rotors, 5 plugs)
 
### Flags
* `-s --strict` will omit any non-alphabetic chars from the ciphertext (more secure, less readable), used only when encrypting
* `-a --accelerate` will attempt to accelerate all calculations using the GPU (OpenCL-compatible hardware required)