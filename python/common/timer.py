import time
from functools import wraps


def timer(part, show_result=True, title='', show_return=True):
    def decorator(f):
        @wraps(f)
        def wrapper(*args, **kwargs):
            start_time = time.perf_counter()
            result = f(*args, **kwargs)
            elapsed_time = time.perf_counter() - start_time
            if elapsed_time < 0.1:
                elapsed_time_str = f'\t\t( {(elapsed_time * 1e3):.3f} ms )'
            else:
                elapsed_time_str = f'\t\t( {elapsed_time:.3f} s )'

            if show_result:
                header = title or f'Part {part} answer'
                print(f'{header}: {result if result and show_return else ""}',
                      elapsed_time_str)
            return result

        return wrapper

    return decorator