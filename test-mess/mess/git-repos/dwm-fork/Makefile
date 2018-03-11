# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = dwm.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

#config.h:
#	@echo creating $@ from config.def.h
#	@cp config.def.h $@

dwm: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p dwm-${VERSION}
	@cp -R Makefile README config.h config.mk \
		${SRC} dwm-${VERSION}
	@tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	@gzip dwm-${VERSION}.tar
	@rm -rf dwm-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f dwm ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dwm

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/dwm
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1

.PHONY: all options clean dist install uninstall
