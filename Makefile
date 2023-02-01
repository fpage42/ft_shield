all: installerMake

binaryExtractorMake:
	@$(MAKE) -C ./binaryExtractor

ft_shieldMake:
	@$(MAKE) -C ./ft_shield

prepareInstaller: binaryExtractorMake ft_shieldMake
	@$(MAKE) run -C ./binaryExtractor

installerMake: prepareInstaller
	@$(MAKE) -C ./installer

clean:
	@$(MAKE) clean -C binaryExtractor
	@$(MAKE) clean -C installer
	@$(MAKE) clean -C ft_shield
