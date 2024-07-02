import '@testing-library/jest-dom';
import { render, screen } from '@testing-library/react';
import { BrowserRouter } from 'react-router-dom';
import { expect, test } from 'vitest';
import { Layout } from '../shared/components/layout/Layout';

test('test layout', () => {
    render(
        <BrowserRouter>
            <Layout>test</Layout>
        </BrowserRouter>,
    );

    const layout = screen.getByTestId('layout-test-id');
    expect(layout).toBeInTheDocument();
});
