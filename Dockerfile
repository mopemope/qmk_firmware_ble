FROM qmkfm/base_container
RUN apt-get update && apt-get -y upgrade && apt-get -y install python-pip
RUN pip install nrfutil

ENV NRFSDK12_ROOT=/qmk_firmware/qmk_util/nRF5_SDK_12.3.0_d7731ad
VOLUME /qmk_firmware
WORKDIR /qmk_firmware
# COPY . .

CMD make clean
