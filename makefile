
.PHONY: TrigEff

all:
	$(MAKE) -C TreeIO
	$(MAKE) -C TrigEff

clear:
	$(MAKE) clear -C TreeIO
	$(MAKE) clear -C TrigEff


TrigEff:
	$(MAKE) -C TrigEff

TreeIO:
	$(MAKE) -C TreeIO