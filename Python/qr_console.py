import qrcode
import numpy as np

def print_qr_in_terminal(data):
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=1,
        border=4,
    )
    qr.add_data(data)
    qr.make(fit=True)

    qr_matrix = qr.get_matrix()
    for row in qr_matrix:
        line = ''.join(['██' if cell else '  ' for cell in row])
        print(line)

if __name__ == "__main__":
    data = "teste"
    print_qr_in_terminal(data)
