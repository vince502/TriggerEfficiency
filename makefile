
.PHONY: TrigEff

all:
	$(MAKE) -C TreeReader
	$(MAKE) -C TrigEff

clear:
	$(MAKE) clear -C TreeReader
	$(MAKE) clear -C TrigEff


TrigEff:
	$(MAKE) -C TrigEff

TreeReader:
	$(MAKE) -C TreeReader