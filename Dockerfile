FROM alpine
RUN apk add alpine-sdk linux-headers
COPY main.c /main.c
RUN cc -o /main /main.c