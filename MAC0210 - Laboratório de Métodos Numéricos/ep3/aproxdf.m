function [ ret_dfx, ret_dfy, ret_dfxy ] = aproxdf(vals, nx, ny, hx, hy)
    ret_dfx  = zeros (nx + 1, ny + 1);
    ret_dfy  = zeros (nx + 1, ny + 1);
    ret_dfxy = zeros (nx + 1, ny + 1);

    for ii = 1:(ny + 1)
        this_dfx = dfx(vals, ii, nx, hx);

        for jj = 1:(nx + 1)
            this_dfy = dfy(vals, jj, ny, hy);

            ret_dfx(ii, jj)  = this_dfx(ii, jj);
            ret_dfy(ii, jj)  = this_dfy(ii, jj);
            ret_dfxy(ii, jj) = dfxy(vals, ii, jj, nx, ny, hx, hy);
        endfor
    endfor
end
