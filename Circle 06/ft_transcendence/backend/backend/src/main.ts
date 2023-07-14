import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { UnauthorizedExceptionFilterFilter } from './auth/unauthorized-exception-filter/unauthorized-exception-filter.filter';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);

  app.enableCors({ origin: process.env.FE_URL });
  
  app.setGlobalPrefix('/api');
  app.useGlobalFilters(new UnauthorizedExceptionFilterFilter());
  await app.listen(process.env.BE_PORT);
}
bootstrap();
