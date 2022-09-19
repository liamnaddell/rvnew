FROM archlinux:latest
RUN yes | pacman -Sy riscv64-elf-gcc vim make qemu-system-riscv
COPY . /opt

WORKDIR "/opt/riscv"

CMD [ "make qemu2" ]
