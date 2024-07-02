import { render, screen } from '@testing-library/react';
import { expect, test } from 'vitest';

import LoadingPage from '../pages/Loading Page/LoadingPage';

test('Test rendering of loading page', () => {
    render(<LoadingPage />);

    const loadingDiv = screen.getByTestId('main-container');
    const spinner = screen.getByTestId('spinner');

    expect(loadingDiv).toBeInTheDocument();
    expect(spinner).toBeInTheDocument();
});
