#pragma once

#include <string>
#include <vector>

#include "main.h"

class ResolutionSettings {
public:
	struct Resolution {
		unsigned width, height, hz;
		Resolution(unsigned w, unsigned h, unsigned z) : width(w), height(h), hz(z) {}
	};

	void readResolution(const char* source);

	size_t getNumResolutions() const { return resolutions.size(); }
	const Resolution& getResolution(int n) const;

	unsigned getActiveWidth() const { return resolutions[activeRes].width; }
	unsigned getActiveHeight() const { return resolutions[activeRes].height; }
	unsigned getActiveHz() const { return resolutions[activeRes].hz; }

	bool setDSRes(const unsigned width, const unsigned height);
	void clearResolutions();
private:
	std::vector<Resolution> resolutions;
	unsigned activeRes = 0;
};

class Settings {
	static Settings instance;
	
	ResolutionSettings resSettings;
	bool inited;
	unsigned baseLogLevel;
	std::vector<string> processingPasses;

	void read(const char* source, bool& value);
	void read(const char* source, int& value);
	void read(const char* source, unsigned& value);
	void read(const char* source, float& value);
	void read(const char* source, std::string& value);
	void read(const char* source, std::vector<std::string>& value);
	
	void log(const char* name, bool value);
	void log(const char* name, int value);
	void log(const char* name, unsigned value);
	void log(const char* name, float value);
	void log(const char* name, const std::string& value);
	void log(const char* name, const std::vector<std::string>& value);

	#define SETTING(_type, _var, _inistring, _defaultval) \
	private: _type _var; \
	public: _type get##_var() const { return _var; };
	#include "settings.def"
	#undef SETTING

	void clearAll();
	void load(const string& fn);

public:
	static Settings& get() {
		return instance;
	}
	static ResolutionSettings& getResSettings() {
		return get().resSettings;
	}
	
	void load();
	
	void report();
	void init();
	void shutdown();
	
	Settings() : inited(false) {
		clearAll();
	}

	void elevateLogLevel(unsigned level);
	void restoreLogLevel();

	unsigned getRenderWidth() { return resSettings.getActiveWidth(); }
	unsigned getRenderHeight() { return resSettings.getActiveHeight(); }
	const std::vector<string>& getProcessingPasses() { return processingPasses; }
};

