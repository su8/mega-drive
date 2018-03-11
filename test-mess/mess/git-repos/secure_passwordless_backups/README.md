secure_passwordless_backups
===========================

The program creates a backup from the given file or directory by utilizing the gpg encryption plus it assigns an **hidden recipient** to the backup (no metadata leaks), so the recipient will be the only person that is able to decrypt the given backup with their private gpg key.

The symmetric encryption embeds the encryption key within every single file, while the asymmetric encryption relies on "public" and "private" keys. The files are encrypted with the public key, and for decryption the private key is used.

Want to verify that no metadata is stored ?

    gpg --list-packets your_encrypted_file.gpg

Should you avoid using Dropbox or MEGA now - no! Since nobody cannot decrypt the backups without your private gpg key !

The **encrypt_decrypt.zsh** file has "encrypt" and "decrypt" functions, so copy it's content and paste it into your shell configuration file or just "source" it.

Make sure to set your preferred keyid in **gpg.conf** example `default-key 0xA97E3564`

Also exchange the trust level of your gpg key, so you won't get asked again and again which key to use for file encryption:

    gpg --edit-key your@email
    trust
    5
    quit


## Requirements

* python2 or python3
* shell (bash, zsh, etc)

Want to use stronger algorithms ? I've wrote a [post](http://wifiextender.github.io/post/gpg-use-stronger-algorithms/) about it in my blog.