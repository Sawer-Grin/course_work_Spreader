import secrets
import string
import os

name_of_env="ZIPPER_PASSWORD"
alphabet = string.ascii_letters + string.digits
password = ''.join(secrets.choice(alphabet) for i in range(20))  # for a 20-character password
os.environ[name_of_env] = password

with open(".temp_env", "w+") as f:
    f.write(name_of_env + "=" + password + "\n")

#if you want
# print(password)