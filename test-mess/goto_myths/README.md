"Jumping" is inevitable part.

See and experience from first hand what consitutes as "jump".

```bash
# unconditional "jump"
for x in 'break.c' 'continue.c' 'return.c' 'goto.c'; do echo "${x}";gcc -O0 -S "${x}" -o - | grep 'jmp';done

# conditional "jump"
for x in j*.c; do echo "${x}";gcc -O0 -S "${x}" -o - | grep 'j';done
```

The examples here represent 2/3 of the available jumps, but still have education purpose.

https://en.wikipedia.org/wiki/X86\_assembly\_language#Program\_flow

https://en.wikibooks.org/wiki/X86\_Assembly/Control\_Flow
