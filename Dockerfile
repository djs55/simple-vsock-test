FROM alpine:3.12 AS build
RUN apk add alpine-sdk linux-headers
COPY main.c /main.c
RUN cc -o /main /main.c

FROM alpine:3.12 AS mirror
RUN mkdir -p /out/etc/apk && cp -r /etc/apk/* /out/etc/apk/
RUN apk add --no-cache --initdb -p /out \
    alpine-baselayout \
    busybox\
    musl \
    strace \
    && true
RUN rm -rf /out/etc/apk /out/lib/apk /out/var/cache

FROM scratch
WORKDIR /
COPY --from=mirror /out/ /
COPY --from=build /main /main
CMD ["/main"]

