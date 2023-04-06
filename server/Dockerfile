FROM node:18.14.2-alpine

RUN addgroup -g 1001 -S nodejs && adduser -u 1001 -D -G nodejs nodejs
RUN chown -R nodejs:nodejs /app

RUN corepack enable pnpm

WORKDIR /app

COPY --chown=nodejs:nodejs . .

RUN pnpm install

ENV DATABASE_URL=file:/logs/sqlite.db

USER nodejs

EXPOSE 9980

CMD ["sh", "-c", "pnpm prisma db push && npm start"]