test:
	$(MAKE) -C test
.PHONY: test

clean:
	$(MAKE) -C test clean
.PHONY: clean

distclean:
	$(MAKE) -C test distclean
.PHONY: distclean
