.PHONY: flash
flash: all
	openocd -f  $(PROJROOT)/oocd.cfg -c "program $(BUILDDIR)/$(PROJECT).elf verify reset" -c "shutdown"

.PHONY: r
r: reset
.PHONY: reset
reset:
	openocd -f $(PROJROOT)/oocd.cfg -c "init" -c "reset" -c "shutdown"
