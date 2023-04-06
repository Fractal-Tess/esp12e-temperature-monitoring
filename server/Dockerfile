FROM node:18.14.2-alpine

RUN corepack enable pnpm
WORKDIR /app

RUN addgroup -g 1001 -S nodejs && adduser -u 1001 -D -G nodejs nodejs

COPY --chown=nodejs:nodejs package.json package.json
RUN pnpm install
RUN chown -R nodejs:nodejs node_modules

COPY --chown=nodejs:nodejs . .

USER nodejs
ENV DATABASE_URL=file:/logs/sqlite.db
EXPOSE 9980

CMD ["sh", "-c", "pnpm prisma db push && pnpm start"]