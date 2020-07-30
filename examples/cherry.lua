-- Note: These values all have defaults. For most users, an empty configuration file will do.
fifo_path = "/tmp/cherry"
desktop_count = 1
border_width = 1
window_gap = 20
top_padding = 1
bottom_padding = 1
right_padding = 1
left_padding = 1

-- This is a Lua script! We can take full advantage of Lua here.
-- Later versions of cherry will provide an API, so that cherry extensions can be written.
print("Hello, world!")

print("The value of fifo_path is: " .. fifo_path)