#!/bin/sh

docker run -ti --rm -v $('pwd'):/qmk_firmware:rw qmk make clean
docker run -ti --rm -v $('pwd'):/qmk_firmware:rw qmk make caravelle_ble/master:mopemope:dfu_ble
docker run -ti --rm -v $('pwd'):/qmk_firmware:rw qmk make caravelle_ble/slave:mopemope:dfu_ble
