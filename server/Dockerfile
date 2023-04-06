FROM node:18.14.2-alpine

RUN apk add --no-cache libc6-compat
RUN apk update

RUN corepack enable pnpm

WORKDIR /app

COPY . .

RUN pnpm install

RUN addgroup -S nodejs && adduser -S nodejs -G nodejs
RUN chown -R nodejs:nodejs /app

EXPOSE 99800

CMD [ "pnpm", "start" ]
