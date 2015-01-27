.PHONY: clean All

All:
	@echo ----------Building project:[ testSelect - Debug ]----------
	@cd "testSelect" && "$(MAKE)" -f "testSelect.mk"
clean:
	@echo ----------Cleaning project:[ testSelect - Debug ]----------
	@cd "testSelect" && "$(MAKE)" -f "testSelect.mk" clean
