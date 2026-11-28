import hashlib
import argparse


def gen_md5_hex(plaintext: str) -> str:
    return hashlib.md5(plaintext.encode("utf-8")).hexdigest()


def starts_with(hash: str, start_str: str = "00000") -> bool:
    if len(hash) < 6:
        return False
    return hash[0:5] == start_str


def get_pos(hex: str) -> int:
    num = int(hex, 16)
    return num if num < 8 else -1


def hack_password(door_id: str) -> str:
    pass_list = list("gggggggg")
    index = 0
    
    while "g" in pass_list:
        hash = gen_md5_hex(door_id + str(index))

        if starts_with(hash):
            pos = get_pos(hash[5])
            if pos != -1 and pass_list[pos] == "g":
                pass_list[pos] = hash[6]
        index += 1

    password = "".join(pass_list)
    return password


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("filename")
    args = parser.parse_args()
    
    with open(args.filename, 'r') as file:
        for line in file:
            print(hack_password(line))
            

if __name__ == "__main__":
    main()
