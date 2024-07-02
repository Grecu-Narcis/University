import '@testing-library/jest-dom';
import { render, screen } from '@testing-library/react';
import { expect, test } from 'vitest';
import { Footer } from '../shared/components/footer/Footer';

test('test footer', () => {
    render(<Footer />);

    const renderedFooter = screen.getByTestId('footer-test-id');
    const footerInner = screen.getByTestId('footer-inner');

    expect(renderedFooter).toBeInTheDocument();
    expect(footerInner).toBeInTheDocument();
});
