
#pragma once

// QT includes
#include <QObject>
#include <QTimer>

// hyperion-utils includes
#include <utils/RgbImage.h>

// Hyperion includes
#include <hyperion/LedString.h>
#include <hyperion/LedDevice.h>
#include <hyperion/PriorityMuxer.h>

// Forward class declaration
namespace hyperion { class ColorTransform; }


class Hyperion : public QObject
{
	Q_OBJECT
public:
	enum Color
	{
		RED, GREEN, BLUE
	};

	enum Transform
	{
		THRESHOLD, GAMMA, BLACKLEVEL, WHITELEVEL
	};

	static LedString createLedString(const Json::Value& ledsConfig);

	Hyperion(const Json::Value& jsonConfig);

	~Hyperion();

	unsigned getLedCount() const;

	void setColor(int priority, RgbColor &ledColor, const int timeout_ms);

	void setColors(int priority, std::vector<RgbColor> &ledColors, const int timeout_ms);

	void setTransform(Transform transform, Color color, double value);

	void clear(int priority);

	void clearall();

private slots:
	void update();

private:
	void applyTransform(std::vector<RgbColor>& colors) const;

	LedString _ledString;

	PriorityMuxer _muxer;

	hyperion::ColorTransform* _redTransform;
	hyperion::ColorTransform* _greenTransform;
	hyperion::ColorTransform* _blueTransform;

	LedDevice* _device;

	QTimer _timer;
};
