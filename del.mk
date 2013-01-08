ifeq ($(DELAY_CLASS),)
DELAY_CLASS = delay_class
endif

INCDIR += $(DELAY_CLASS)
CPPSRC += $(DELAY_CLASS)/delayclass.cpp