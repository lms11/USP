% Save image using PPM P3 file format

function save_image(red, green, blue, output)

    width  = min([ columns(red), columns(green), columns(blue) ]);
    height = min([ rows(red), rows(green), rows(blue) ]);

    % Open file
    fid = fopen (output, "w");

    % Print all values of PPM
    % See reference: https://www.cs.swarthmore.edu/~soni/cs35/f13/Labs/extras/01/ppm_info.html
    fprintf (fid, "P3\n");
    fprintf (fid, "%d %d\n255\n", width, height);
    for ii = 1:height
        for jj = 1:width
            fprintf (fid, "%d %d %d ", red(ii, jj), green(ii, jj), blue(ii, jj));
        endfor
        fprintf (fid, "\n");
    endfor

    % Close files
    fclose (fid);
endfunction
