import express from 'express';
import bodyParser from 'body-parser';
import { z } from 'zod';
import { PrismaClient } from '@prisma/client';

const prisma = new PrismaClient();
const PORT = 9980;
const app = express();

app.use(bodyParser.json());

const validator = z.object({
  temperature: z.number(),
  humidity: z.number(),
});

app.post('/temperature', async (req, res) => {
  const temp = validator.safeParse(req.body);
  if (!temp.success) {
    res
      .status(400)
      .json({
        message: temp.error.message,
      })
      .end();
    return;
  }
  await prisma.log.create({
    data: {
      ...temp.data,
    },
  });

  res.status(200).end();
});

app.listen(PORT, () => {
  console.log(`Listening on port ${PORT}`);
});
