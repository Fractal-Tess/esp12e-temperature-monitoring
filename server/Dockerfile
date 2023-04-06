FROM node:18.14.2-alpine

RUN apk add --no-cache libc6-compat
RUN apk update

RUN corepack enable pnpm

WORKDIR /app

COPY . .

RUN pnpm install

RUN chown -R node:node /app

ENV DATABASE_URL=file:/logs/sqlite.db

EXPOSE 9980

CMD ["sh", "-c", "pnpm prisma db push && npm start"]