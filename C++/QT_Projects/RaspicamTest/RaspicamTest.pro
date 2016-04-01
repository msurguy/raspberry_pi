TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    raspicam/private/mutex.cpp \
    raspicam/private/private_impl.cpp \
    raspicam/private/threadcondition.cpp \
    raspicam/private/yuv_conversion.cpp \
    raspicam/raspicam.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    raspicam/private/exceptions.h \
    raspicam/private/mutex.h \
    raspicam/private/private_impl.h \
    raspicam/private/private_types.h \
    raspicam/private/threadcondition.h \
    raspicam/private/yuv_conversion.h \
    raspicam/raspicam.h \
    raspicam/raspicamtypes.h \
    raspicam/scaler.h \
    raspicam/mmal/mmal.h \
    raspicam/mmal/mmal_buffer.h \
    raspicam/mmal/mmal_common.h \
    raspicam/mmal/mmal_component.h \
    raspicam/mmal/mmal_connection.h \
    raspicam/mmal/mmal_default_components.h \
    raspicam/mmal/mmal_encodings.h \
    raspicam/mmal/mmal_events.h \
    raspicam/mmal/mmal_format.h \
    raspicam/mmal/mmal_metadata.h \
    raspicam/mmal/mmal_parameters.h \
    raspicam/mmal/mmal_parameters_camera.h \
    raspicam/mmal/mmal_parameters_common.h \
    raspicam/mmal/mmal_parameters_video.h \
    raspicam/mmal/mmal_pool.h \
    raspicam/mmal/mmal_port.h \
    raspicam/mmal/mmal_queue.h \
    raspicam/mmal/mmal_types.h \
    raspicam/mmal/mmal_util.h \
    raspicam/mmal/mmal_util_params.h \
    mmal/mmal.h \
    mmal/mmal_buffer.h \
    mmal/mmal_common.h \
    mmal/mmal_component.h \
    mmal/mmal_connection.h \
    mmal/mmal_default_components.h \
    mmal/mmal_encodings.h \
    mmal/mmal_events.h \
    mmal/mmal_format.h \
    mmal/mmal_metadata.h \
    mmal/mmal_parameters.h \
    mmal/mmal_parameters_camera.h \
    mmal/mmal_parameters_common.h \
    mmal/mmal_parameters_video.h \
    mmal/mmal_pool.h \
    mmal/mmal_port.h \
    mmal/mmal_queue.h \
    mmal/mmal_types.h \
    mmal/mmal_util.h \
    mmal/mmal_util_params.h

