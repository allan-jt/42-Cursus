import { ArgumentsHost, Catch, ExceptionFilter } from '@nestjs/common';

@Catch()
export class UnauthorizedExceptionFilterFilter<T> implements ExceptionFilter {
  catch(exception: T, host: ArgumentsHost) {
    const ctx = host.switchToHttp();
    const response = ctx.getResponse();

    // Handle the exception as needed
    response.status(401).json({ message: 'Unauthorized' });
  }
}
