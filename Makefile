.PHONY: clean All

All:
	@echo "----------Building project:[ opti-kergo - Debug ]----------"
	@"$(MAKE)" -f  "opti-kergo.mk"
clean:
	@echo "----------Cleaning project:[ opti-kergo - Debug ]----------"
	@"$(MAKE)" -f  "opti-kergo.mk" clean
