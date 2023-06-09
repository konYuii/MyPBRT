#pragma once
#ifndef __DisplayWidget_h__
#define __DisplayWidget_h__

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QCloseEvent>

#include "IMAGraphicsView.h"

#include "Core/FrameBuffer.h"
#include "RenderThread.h"

class DisplayWidget : public QGroupBox {
	Q_OBJECT


public:
	DisplayWidget(QGroupBox * parent = Q_NULLPTR);
	~DisplayWidget();

	void startRenderThread();
	void killRenderThread();

public:
	bool renderFlag;
	RenderThread * rThread;
	FrameBuffer framebuffer;

private:
	QGridLayout displayWidgetLayout;

	IMAGraphicsView m_IMAGraphicsView;

	void closeEvent(QCloseEvent *event);

private slots:
	void PrintString(char* s);
	void PrintDataD(const char* s, const double data);
};







#endif








