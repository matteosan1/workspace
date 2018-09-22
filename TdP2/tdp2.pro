TEMPLATE = subdirs

SUBDIRS = clone  \
          asn1   \
          common \
          server \
          client

clone.subdir  = clone
asn1.subdir   = asn1
common.subdir = common
client.subdir = client
server.subdir = server

client.depends = clone common asn1
server.depends = clone common asn1

# add target to generate asn1
message(genereting asn1...)
MKASN1 = true
    && cd asn1 \
    && rm -fr src include generated_asn \
    && mkdir src \
    && mkdir include \
    && mkdir generated_asn \
    && cd generated_asn \
    && echo "Working dir: $PWD" \
    && asn1c ../*.asn1 -fwide-types \
    && rm -f converter-sample.c \
    && mv *.h ../include \
    && mv *.c ../src \
    && cd .. \
    && rm -fr generated_asn \
    && cd ..

asn1.target = asn1
asn1.commands = $$MKASN1
QMAKE_EXTRA_TARGETS += asn1

