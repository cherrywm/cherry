-- Note: These values all have defaults. For most users, an empty configuration file will do.
fifo_location = "/tmp/cherry"
desktop_count = 1

-- This is a Lua script! We can take full advantage of Lua here.
-- Later versions of cherry will provide an API, so that cherry extensions can be written.
print("Hello, world!")

print("The value of fifo_location is: " .. fifo_location)